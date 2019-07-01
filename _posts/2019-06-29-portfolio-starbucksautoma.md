---
title: Starbucks Automatic Scheduler
categories: portfolio
featured_img: /assets/portfolios/starbucks_automa
---

See the project [here](https://google.com/)

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


#### __init__(self)

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

