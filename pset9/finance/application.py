import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Added by ren: tokens + datatime
# secret token: pk_376b7a563e114e1dbd4375bfe65f6fb5, use the line under in terminal, Renatko
# export API_KEY=pk_376b7a563e114e1dbd4375bfe65f6fb5
import datetime
datetime.datetime.now()
datetime.datetime(2009, 1, 6, 15, 8, 24, 78915)

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Display the entries in the database on index.html

    # Find currently owned cash by user
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    users_cash = rows[0]["cash"]

    # Find currently owned stocks by user
    rows = db.execute("SELECT * FROM stock WHERE users_id = ?", session["user_id"])

    # Show users portfolio with current prices
    n = 0
    summary = users_cash

    for something in rows:

        single_symbol = rows[n]["symbol"]
        RESULTS = lookup(single_symbol)

        # Check full name and current price of each stock
        rows[n]["name"] = RESULTS["name"]
        rows[n]["current_price"] = RESULTS["price"]

        # Calculate total value of each holding (shares times price)
        total_value = rows[n]["shares"]*RESULTS["price"]
        rows[n]["total"] = usd(total_value)

        # Calculate summary
        summary += total_value

        n = n+1

    return render_template("index.html", rows=rows, summary=usd(summary), cash=usd(users_cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure shares is a number (so if can be compiled to a number; a word can't)
        try:
            asked_shares = float(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a number", 400)

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure number of shares was submitted and is a positive number
        if not asked_shares or not float(asked_shares) > 0:
            return apology("must provide positive number of shares", 400)

        # Ensure number of shares is not a fractional number
        if float(asked_shares) % 1 != 0:
            return apology("must provide non-fractional number of shares", 400)

        # Check if the symbol exists
        RESULTS = lookup(request.form.get("symbol"))

        if RESULTS is None:
            return apology("Symbol not exists", 400)

        # Check if user can afford to buy

        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        users_cash = rows[0]["cash"]

        purchase = RESULTS["price"]*int(asked_shares)
        new_cash = users_cash - purchase

        # no, render an apology
        if users_cash < purchase:
            return apology("not enough cash", 403)

        # yes, complete the purchase
        if users_cash >= purchase:

            # Adjust table users
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])

            # Adjust table history
            db.execute("INSERT INTO history (users_id, symbol, shares, price_buy, price_sell, time_sell) VALUES (?, ?, ?, ?, ?, ?)",
                       session["user_id"], RESULTS["symbol"], int(asked_shares), RESULTS["price"], '', '')

            # Adjust table stock

            # Check if user already have shares of that stock
            rows = db.execute("SELECT * FROM stock WHERE users_id = ? AND symbol = ?",
                              session["user_id"], request.form.get("symbol"))

            # yes. Update row
            if len(rows) == 1:

                # Calculate the average of prices
                rows = db.execute("SELECT price_buy, shares FROM stock WHERE users_id = ? AND symbol = ?",
                                  session["user_id"], RESULTS["symbol"])
                old_price = rows[0]["price_buy"]
                old_shares = rows[0]["shares"]

                average_price = (old_price*old_shares + RESULTS["price"]*int(asked_shares)) / (old_shares + int(asked_shares))
                print(average_price)

                db.execute("UPDATE stock SET shares = shares + ?, price_buy = ?, price_sell = ?, time_sell = ? WHERE users_id = ? AND symbol = ?",
                           int(asked_shares), RESULTS["price"], '', '', session["user_id"], RESULTS["symbol"])

                # Redirect user to home page
                return redirect("/")

            # no. Add new row
            if len(rows) != 1:
                db.execute("INSERT INTO stock (users_id, symbol, shares, price_buy, price_sell, time_sell) VALUES (?, ?, ?, ?, ?, ?)",
                           session["user_id"], RESULTS["symbol"], int(asked_shares), RESULTS["price"], '', '')

                # Redirect user to home page
                return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Find users history
    rows = db.execute("SELECT * FROM history WHERE users_id = ?", session["user_id"])

    # Show users history
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        RESULTS = lookup(request.form.get("symbol"))

        # show error message, if the result not found
        if RESULTS is None:
            return apology("Result not found", 400)

        # show result if found (price shown specially by usd function - hidden requirement from CS50)
        usd_price = usd(RESULTS["price"])
        return render_template("quoted.html", results=RESULTS, usd_price=usd_price)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    redirect("/register")
    """Register user"""

    # Require that a user input a username
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password again was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password again", 400)

        # Ensure passwords match
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # yes, user already exists
        if len(rows) == 1:
            return apology("username already exists", 400)

        # no, new user
        if len(rows) != 1:

            # Add the user's entry into the database, store a hash of the user’s password

            hashed_password = generate_password_hash(request.form.get("password"))

            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), hashed_password)

            # Automatically log in the user
            rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
            session["user_id"] = rows[0]["id"]

            # Redirect user to home page
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Check number of users shares
        rows = db.execute("SELECT shares FROM stock WHERE users_id = ? AND symbol = ?",
                          session["user_id"], request.form.get("symbol"))

        users_shares = rows[0]["shares"]

        asked_shares = request.form.get("shares")

        # Ensure input was insert and is a positive integer
        if not asked_shares or not int(asked_shares) > 0:
            return apology("must provide positive number of shares", 400)

        # Ensure user owns enough shares

        # no
        if users_shares < int(asked_shares):
            return apology("not enough shares", 400)

        # yes, complete the sell
        if users_shares > int(asked_shares):

            RESULTS = lookup(request.form.get("symbol"))
            current_price = RESULTS["price"]

            selling_price = current_price*int(asked_shares)

            # Adjust table users
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", selling_price, session["user_id"])

            # Adjust table history; add '-' by shares means selling
            db.execute("INSERT INTO history (users_id, symbol, shares, price_buy, time_buy, price_sell) VALUES (?, ?, ?, ?, ?, ?)",
                       session["user_id"], RESULTS["symbol"], '-' + asked_shares, '', '', current_price)

            # Adjust table stock
            db.execute("UPDATE stock SET shares = shares - ?, price_sell = ?, time_sell = ? WHERE users_id = ? AND symbol = ?",
                       int(asked_shares), current_price, datetime.datetime.now(), session["user_id"], request.form.get("symbol"))

            # Redirect user to home page
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        # Query database for stocks symbols, which user currently has
        rows = db.execute("SELECT symbol FROM stock WHERE users_id = ? AND shares > 0", session["user_id"])

        # Creating a list of symbols, which user currently has
        symbols = []

        # Inserting a string into a list (without getting split into characters)
        n = 0
        for row in rows:

            new_symbol = rows[n]["symbol"]
            symbols.append(new_symbol)
            n = n+1

        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
