> Tobias de Bildt  
> 1023603  
> 31-03-2023

# Readme

## Where are the files?
| Item                     | Location            |
|--------------------------|---------------------|
| Microcontroller code     | `./ESP32-code/`     |
| Certificates for web-app | `./chat-app/certs`  |
| Web-app                  | `./chat-app/public` |
| README.md                | `./`                |
| Demo video               | `./`                |

<br>

***
<br>

## Using the bot from [netwerkenbasis.com](netwerkenbasis.com)
To use the bot from the [netwerkenbasis.com](netwerkenbasis.com), first navigate to the URL. When you first visis the webpage, you will be prompted for your user:pass, you will need to fill in "student:welkom01". You have succesfully logged in, now you can start entering commands. For a list of commands, see the final segment of this guide. 

<br>

***
<br>

## Using the bot from a locally hosted web-app

### Starting the app
To host this webapp locally, you first need to enter the chat-app repository:

`cd chat-app`

In the chat-app directory, run the following command to start the app (docker required):

`docker-compose up -d`

### Using the app
To use the app, connect to `https://localhost` from your browser. In the first prompt fill in "student" and in the second prompt fill in "welkom01". If all went well, you should be logged in and ready to use the bot. For commands, see the next segment of this guide.

<br>

***
<br>

## Commands

| Command                | Function                               |
|------------------------|----------------------------------------|
| `BOT-1023603: led:aan` | Turns on the LED                       |
| `BOT-1023603: led:uit` | Turns off the LED                      |
| `BOT-1023603: temp`    | Returns the current temperature (in °C)|

<br>

***
<br>