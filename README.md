# IRC
IRC in cpp98

### Checklist

- [x] Executable name are "ircserv"
- [x] Executable need two arguments: port and password
- [x] The server capable of handling multiple client
- [x] The client and server communicate via TCP/IP
- [ ] Features
  - [x] Set nickname
  - [ ] Set username
  - [x] Join a channel
  - [x] send private message
  - [x] recive private message
  - [x] message in channel
  - [ ] channel operator users
  - [x] channel basic users
  - [ ] Channel operator commands
    - [x] KICK a client from a channel
    - [x] INVITE a client to a channel
    - [ ] TOPIC change th channel topic
    - [ ] TOPIC view the channel topic
    - [ ] MODE change the channel's mode
      - [x] i: Set Invite only
      - [x] i: Remove Invite only
      - [x] t: Set TOPIC command restriction
      - [x] t: Remove TOPIC command restriction
      - [ ] k: Set channel key
      - [ ] k: Remove channel key
      - [x] o: Give operator privilege
      - [x] o: Remove operator privilege
      - [x] l: Set user limit
      - [x] l: Remove user limit