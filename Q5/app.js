const fs = require("fs");
const express = require("express");
const path = require("path");

const dotenv = require('dotenv');
dotenv.config({path: './.env'});

const mysql = require('mysql');

const app = express()

const db = mysql.createConnection({
    host: process.env.HOST,
    user: process.env.USER,
    password: process.env.PASSWORD,
    multipleStatements: true,
    port:3306,
    database: "bitnine"
});

db.connect((error)=>{
    
    try {
        db.query("CREATE DATABASE bitnine", (error)=>{
            db.query("USE bitnine; CREATE TABLE user (id int(11) AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255) NOT NULL, email VARCHAR(255) NOT NULL, password VARCHAR(255) NOT NULL)")
            console.log("database and table created successfully");
        });
        
    } catch (error) {
        console.log(error);
    }

})

app.set("view engine", 'hbs');

app.use(express.json());
app.use(express.urlencoded({extended:false}));

app.use(express.static(path.join(__dirname, '/public')));
app.use('/css', express.static(path.join(__dirname, "node_modules/bootstrap/dist/css")));
app.use('/js', express.static(path.join(__dirname, "node_modules/bootstrap/dist/js")));


app.use("/", require("./routes/pages"));
app.use("/auth", require("./routes/auth"));

app.listen(3001, () => {
    console.log("app running on port 3000");
  });