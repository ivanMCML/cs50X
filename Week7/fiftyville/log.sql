-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT *
FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2024
AND street = "Humphrey Street";

-- Theft took place at 10:15am at bakery
-- All three witnesses were interviewed and mantioned bakery in their interviews
-- crime_scene_report id is 295



-- Find interviews that have bakery mantioned
SELECT *
FROM interviews
WHERE day = 28 AND month = 7 AND year = 2024
AND transcript LIKE "%bakery%";

-- Within 10min of the theft, thief's car was in the bakery parking lot
-- Earlier in the morning, thief withdrawed some money at the ATM on Leggett Street
-- AS the thief was leaving the bakery, he had a call shorter then a minute. The thief asked the person on the other end of the phone to purchase the ticket for earliest flight tomorrow.



-- Find information about people who withdrawed money at ATM on Leggett Street and has a car that left bakery parking lot after the crime
SELECT people.*
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN(
    SELECT account_number
    FROM atm_transactions
    WHERE day = 28 AND month = 7 AND year = 2024
    AND atm_location = "Leggett Street" AND transaction_type = "withdraw")
AND people.license_plate IN(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2024
    AND hour = 10 AND minute > 14 AND minute < 26);

-- LIST OF SUSPECTS
-- name     phone number    passport number
-- Bruce    (367) 555-5533  5773159633
-- Diana    (770) 555-1861  3592750733
-- Iman     (829) 555-5269  7049073643
-- Luca     (389) 555-5198  8496433585



-- Find person who had a short call immediately after crime
SELECT *
FROM phone_calls
WHERE year = 2024 AND month = 7 AND day = 28
AND durationn < 60;

-- LIST OF SUSPECTS
-- Bruce
-- Diana

-- LIST OF SUSPECTS FOR ACCOMPLICE
-- Bruce called (375) 555-8161
-- Diana called (725) 555-3243



-- Find earliest flight
SELECT *
FROM flights
WHERE year = 2024 AND month = 7 AND day = 29;

-- Id od the earliest flight is 36



-- Find who
SELECT passengers.passport_number, airports.*
FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.id = 36
AND (passengers.passport_number = 5773159633 OR passengers.passport_number = 3592750733);

-- THIEF IS BRUCE
-- BRUCE ESCAPED TO NEW YORK CITY



-- Find whose number Bruce calles
SELECT name
FROM people
WHERE phone_number = "(375) 555-8161";

-- ROBIN WAS ACCOMPLICE
