## Prerequisites
- XAMPP server for MySQL
- Nodejs installed
- NPM installed
- MySQL installed

## Running The code
1) Start the XAMPP server as it's needed to run the MySQL server. 
2) Clone the repository
  ```
  git clone https://github.com/Mariam22-hub/bitnineTask/tree/main
  ```
3) Navigate to the Q5 folder
  
4) create a **.env** file and add the following:
 ```
  HOST=localhost
  USER=root
  PASSWORD=""
  JWT_EXPIRE_TIME = '60d'
  JWT_SECRET_KEY = 'secret_key'
  DATABASE = bitnine
```
5) Start the server
```
npm start
```
6) Type ``` http://localhost:3001``` into the browser to access the main page 
