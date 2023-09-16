const username = prompt('Enter your username:');
const password = prompt('Enter your password:');
const clientID = 'user-' + (Math.floor(Math.random() * 10000) + 10000).toString().substring(1)

let myMessage

const mqttClient = mqtt.connect('wss://netwerkenbasis.com:1884', {
       username: username,
        password: password
       });


      

      mqttClient.on('connect', function () {
        console.log('Connected to MQTT broker');

        mqttClient.subscribe('chat/message', function (err) {
          if (err) {
            console.error('Cant subscribe to topic:', err);
          } else {
            console.log('Subscribed to topic: chat/message');
            mqttClient.publish('chat/message', username + "(" + clientID + ")" + ' joined the chat');
          }
        });
      });

      mqttClient.on('message', function (topic, message) {
        console.log('Received message on topic', topic, ':', message.toString());

        document.getElementById("userfield").innerHTML = "Your username is: " + username;
        document.getElementById("idfield").innerHTML = "Your clientID is: " + clientID;

        const li = document.createElement('li');
        li.textContent = message.toString();

        if (message.toString() == myMessage) {
          li.classList.add('sent');
        } else {
          li.classList.add('received');
        }
        message == null
        document.getElementById('messages').appendChild(li);
        scrollToBottom()
      });
        
      document.querySelector('form').addEventListener('submit', function (event) {
        event.preventDefault();
        
        const message = document.getElementById('message').value;
        // save message to see difference between own and different messages.
        myMessage = message
        mqttClient.publish('chat/message', message);
        document.getElementById('message').value = '';
      });

      function scrollToBottom() {
        const messages = document.getElementById('messages');
        messages.scrollTop = messages.scrollHeight;
      }