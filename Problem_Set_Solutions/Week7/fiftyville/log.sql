-- Keep a log of any SQL queries you execute as you solve the mystery.

-- First I found out which tables I had access to
.tables
-- Then I found out how the tables are connected and what is contained inside
.schema
-- Crime Scene Reports interested me
.schema crime_scene_reports
-- Wanted to find out some descriptions of crimes committed on July 28th 2023 on Humphrey Street
SELECT id, description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2023 AND street = 'Humphrey Street';
-- From this, I found out the CS50 duck was stolen at 10:15am at the Humphrey Street bakery, with 3 witnesses all mentioning the bakery.
-- I first wanted to find out what the witnesses had to say. First I need to see what's in the Interviews table.
.schema interviews
-- I didn't know what the name column was for so wanted to find out
SELECT name FROM interviews LIMIT 10;
-- Now need to see the transcripts
SELECT id, name, transcript FROM interviews WHERE year = 2023 AND month = 7 AND day = 28;
-- Ruth says that the thief got into a car and drove away, and suggested looking at cars that left the bakery parking lot within 10 mins of the theft.
-- Raymond says that the thief was on the phone for less than a minute and called someone about purchasing a flight ticket.
-- Eugene says he saw the thief withdrawing money earlier that morning on Leggett Street. Following up on this:
.schema atm_transactions
-- Check which locations are in that table
SELECT DISTINCT atm_location FROM atm_transactions;
-- Check the transactions earlier that morning on Leggett Street
SELECT account_number, transaction_type, amount FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';
-- Nothing suspicious, so going to check the phone calls table
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2023 AND month = 7 and day = 28 AND duration <= 60;
-- Just had an idea with the bank accounts
.schema bank_accounts
.schema people
-- Going to try and see which people's names come up when searching for people who withdrew money from the bank and also made a phone call under 60 seconds
SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
    )
)AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration <= 60
);
--Seems to be effective, as it narrowed the search down to 5 people. Now, going to follow up on the 3rd lead, regarding the car escape.
.schema bakery_security_logs
-- Going to check the logs for the day of the robbery. The car left within 10 minutes of the theft according to Ruth, and the crime report said it happened at 10:15am
SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- Now going to assign these plates to names and check which names coincide with the other list of 5 names.
SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
    )
)AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration <= 60
)AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
);
-- The list is down to 2 names: Diana and Bruce.
-- Raymond also mentioned in his interview that the thief called someone, planning to take the earliest flight out of Fiftyville the next day, i.e. July 29th
.schema flights
.schema airports
-- I need to find out what fiftyville's airport is called
SELECT * FROM airports WHERE city = 'Fiftyville';
-- The airport is called CSF - Fiftyville Regional Airport (id 8). Now I need to check which flights were the earliest out of fiftyville the day after the theft.
SELECT id, destination_airport_id, hour, minute FROM flights WHERE year = 2023 AND month = 7 AND day = 29 AND origin_airport_id = 8 ORDER BY hour ASC, minute ASC LIMIT 1;
-- The earliest flight was id 36 taken out of Fiftyville Regional Airport was at 8:20am to airport with id 4. Time to check which passengers were onboard.
.schema passengers
.schema people
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
-- I notice Bruce appeared in this list. Just to confirm, I will combine all clues together into one big query.
SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
    )
)AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration <= 60
)AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
)AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
        SELECT id
        FROM flights
        WHERE year = 2023 AND month = 7 AND day = 29
        AND origin_airport_id = 8 ORDER BY hour ASC, minute ASC LIMIT 1)
);
-- Bruce remains as the only possible suspect. Therefore he must be the thief!
-- Now I need to find out which city he escaped to. I can do this using the query from before, where I found out the destination airport id was 4. But just to confirm:
SELECT city FROM airports WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE year = 2023 AND month = 7 AND day = 29
    AND origin_airport_id = 8 ORDER BY hour ASC, minute ASC LIMIT 1
);
-- The city he escaped to was New York City!
-- To find Bruce's accomplice I can find out who he called when he robbed the store and asked for them to buy the plane ticket.
SELECT name
FROM people
WHERE phone_number = (
    SELECT receiver
    FROM phone_calls
    WHERE caller = (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
    AND year = 2023 AND month = 7 AND day = 28
);
-- The accomplice is Robin!
