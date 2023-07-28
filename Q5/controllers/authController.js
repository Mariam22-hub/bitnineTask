const mysql = require('mysql');
const jwt = require("jsonwebtoken");
const bcrypt = require("bcryptjs");
const dotenv = require('dotenv');

dotenv.config({path: './.env'});

const db = mysql.createConnection({
    host: process.env.HOST,
    user: process.env.USER,
    password: process.env.PASSWORD,
    multipleStatements: true,
    port:3306,
    database: process.env.DATABASE
});


exports.register = (req, res)=>{
    console.log(req.body);

    const {name, email, password, passwordConfirm} = req.body;

    db.query('SELECT email FROM user where email = ?;', [email], async (error, result)=>{
        console.log(result)
        if (error){
            console.log(error);
        }
        else {
            if (result.length > 0){
                return res.render('register', {
                    message: "That email is already in use"
                })
            }
            else if (password !== passwordConfirm){
                return res.render('register', {
                    message: "Passwords Do Not match!"
                })
            }
        }

        let hashedPass = await bcrypt.hash(password, 8);

        db.query("INSERT INTO user SET ?;", {name:name, email:email, password:hashedPass}, (error2, ress)=>{

            try{

                const token = jwt.sign({ email: req.body.email}, process.env.JWT_SECRET_KEY, {expiresIn:process.env.JWT_EXPIRE_TIME,});

                return res.render('login', {
                    message: "You Registered Successfully. Now login to view Bitnine!"
                })
            }   
            catch(err){
                console.error(err.message);
                // ress.status(500).send({ error: 'Internal Server Error' });     
            }
   
        });
    });
}

exports.login = async (req, res)=>{

    console.log(req.body);

    const {email, password} = req.body;

    try {
        // const registeredUser = await db.query(`USE BITNINE; SELECT * FROM user WHERE email = "${email}"`);
        // console.log(registeredUser)

        db.query(`SELECT * FROM user WHERE email = "${email}"`, async (error, data)=>{
            
            // data = JSON.parse(JSON.stringify(data));
            console.log(data)
            if (data.length > 0){
                
                const d = JSON.parse(JSON.stringify(data))

                console.log(d)

                const authorization = await bcrypt.compare(
                    req.body.password,
                    d[0].password
                );

                console.log(authorization);

                if (!authorization)
                    return res.status(400).json({ message: "Password is incorrect." });

                
                const token = jwt.sign({ email: req.body.email }, process.env.JWT_SECRET_KEY, {
                    expiresIn: process.env.JWT_EXPIRE_TIME,
                });
                
                console.log(token);

                // return res.send("welcome back!");
                return res.redirect("bitnine");
            }
            else {
                return res.status(404).json({ message: "User doesn't exist" });
            }
        });

    } catch (error) {
        res.status(404).json({
            message: "invalid username or password",
            status: false
        })
    }
}

exports.bitnine = (req,res)=>{
    
    res.render('bitnine');
}