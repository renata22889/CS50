-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Read description of crime scene report at the day and place of crime
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses
-- who were present at the time — each of their interview transcripts mentions the courthouse.
-- new hints: time of theft: 10:15; place of theft: courthouse; 3 witnesses

-- Read intervies from the day of crime of the 3 witnesses
SELECT name, transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- new hints: call for lesst than 1 min. Than drive away from the courthouse parking lot. Eugene konws theft. Withdraw money from ATM on Fifer Street. Theft order flight for next day.

-- Find abbreviation of airport in Fiftyville
SELECT id FROM airports WHERE city = "Fiftyville";
8

-- Find flights from next day and choose the earliest one
SELECT id, destination_airport_id, hour, minute FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville");
id | destination_airport_id | hour | minute
18 | 6 | 16 | 0
23 | 11 | 12 | 15
36 | 4 | 8 | 20
43 | 1 | 9 | 30
53 | 9 | 15 | 20
-- Hints : the thief escaped with the earliest flight of number: 36, to city nb 4

-- and destination is:
SELECT city FROM airports WHERE id = 4;
-- Destination is London

-- Find people, based on: phone number, license plate
SELECT name, passport_number FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND
license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND activity = "exit" AND hour = 10);

name | passport_number
Roger | 1695452385
Madison | 1988161715
Russell | 3592750733
Evelyn | 8294398571
Ernest | 5773159633

-- select who among them withdraw money
SELECT name, passport_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street")
AND person_id IN
(SELECT id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND
license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND minute < 35)));

name | passport_number
Russell | 3592750733
Ernest | 5773159633

-- select who among them was passenger of flight id 36 on next day
SELECT name, passport_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street")
AND person_id IN
(SELECT id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND
license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND minute < 35)))
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

name | passport_number
Ernest | 5773159633
-- the Thief is Ernest

-- Check who Ernest was calling to:

SELECT phone_number FROM people WHERE name = "Ernest";
-- Ernest phone nb is: (367) 555-5533

SELECT receiver FROM phone_calls WHERE caller = "(367) 555-5533" AND year = 2020 AND month = 7 AND day = 28 AND duration < 60;
-- Receiver has phone nb: (375) 555-8161

SELECT name FROM people WHERE phone_number = "(375) 555-8161";
-- Accomplice is Berthold

