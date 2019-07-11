---
title: Starbucks Automatic Scheduler
categories: Portfolio
featured_img: /assets/portfolios/starbucks_automa
---

See the project [here](https://github.com/JaredDyreson/starbucks_automa_production)

# Introduction

This project was written to automatically log into my Starbucks Portal and input my schedule into Google Calendar. I have rewritten the code base on three separate occasions, twice to reduce the size/bloat and once out of necessity.

# How it works

## time_struct

time_struct is a calendar object struct to help aide in the facilitation of collecting start and end times for the Google Calendar API POST request.

We have basic compare statements, allowing the use of `==` and `!=` operators. 
Since we don't have to rely on some weird parsing function to split variables, we have a much greater range of freedom when implementing in the driver code.

## addingEvents

Here we borrow some code from the [getting started](https://developers.google.com/calendar/quickstart/python). This is a fantastic resource and walks through the various requirements needed to get working with the Google Calendar API. Continuing forward, it is expected that you read the previous link to obtain your `token.pickle` file and placing it in the appropriate folder.

### GoogleEventHandler

To make the process easier in driver code, most of the heavy lifting is handled in this class alone. 
We are only needed to instantiate one of these objects at a time as it can reuse the credentials generated in `gen_credentials`, allowing for a cleaner code base.


#### __init__

We get our credentials and service attribute which will allow for communication between the program and the Google Calendar API.

#### gen_credentials

Credentials are stored in a predefined path `/home/$USER/Applications/starbucks_automa/credentials`.
This directory structure is put into place by the installer script and is expected that the end user will place `token.pickle` in this directory. 
Another file, `credentials.json` is also place in this directory and is used to answer the following questions; username, password, two factor authentication. 
Since this program was written to accommodate for one user, it is paramount that you first attempt to login and take note of the questions asked. 
Then, make a pull request indicating that you wish to add more two factor authentication questions to the program.
`credentials` is returned to allow for authentication for Google Calendar API requests.

#### add_event

This function accepts an event in JSON format with the following structure:

```json
{
    "summary": "SOMEONE's Work",
    "start": {
        "dateTime": "START TIME",
        "timeZone": "CURRENT TIME ZONE"
    },
    "end": {
        "dateTime": "END TIME",
        "timeZone": "CURRENT TIME ZONE"
    },
    "location": "WORK LOCATION"
}
```
Start and end time **must** be in this date format `%Y-%m-%dT%H:%M:%S-OFFSET`, where the offset is the amount of hours different from UTC. 
For example, Los Angeles has an offset of seven hours so it would look something like this: `%Y-%m-%dT%H:%M:%S-07:00`.
We make a `time_struct` object to get human readable dates and to check if the event has already been inputted. This checking is done using the `get_free_busy` function. We check if the event is *not* in the calendar to proceed. We get a message telling us if it was added or has already been added.

#### get_events

Return a list of the next fifty events we have access to.

#### gen_time_struct

Check if any part of the incoming event JSON data is `None` then proceed to load up the proper attributes of the struct.
Lastly return the object.

#### get_free_busy

**False:** you are not busy

**True:** you are busy

The way that freebusy request works is that you cannot just specify the start and end time of the event
Use the start and add an hour to the end time, it should work from there.

We send a request giving the start (timeMin), end (timeMax), time zone, and the proper calendar (primary).

Parsing the request allows us to check if we are busy.
The list of events retrieved length can be an easy indication and it's length being zero means we are free.
The second method is by looping through the list and checking if start and end time provided match an element in the list.
If it finds something, then we return `True`, else we return `False`.

## driver_utils

Here we are using the Firefox driver gain access to certain elements to further the program flow.

### findUserName

This page can be temperamental.
We need to add a `try-catch` block to check if text input box surrounded in black is present.
If our element has not loaded, we wait four seconds to hopefully allow time for the element to render.
Notice the method chaining in the `try-catch` block; we are able to directly use our `JSONParser` class directly in the `send_keys` function.


![Find Username Field](https://jareddyreson.github.io/assets/starbucks/first_landing_page)
