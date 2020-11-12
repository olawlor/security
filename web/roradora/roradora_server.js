/*
Node JS cryptocurrency server.


*/
var express = require('express');

var escape = require('escape-html');
var pre=function(text) {
	return "<pre>"+escape(text)+"</pre>";
}

var request = require('request');
var app = express();
var bodyParser = require('body-parser')
// parse POST data
app.use(bodyParser.urlencoded({ extended: false }))
// Serve static files from the "static/" directory:
app.use(express.static('static/'));

// This is an in-memory database of the account names & balances
var accounts={};


app.get('/', function(req, res) {
  res.send('This is not for you.');
});

var OKhex=/^[a-f0-9]+$/;
app.all('/roradora/register', function(req, res) {
  var pubkey=req.query.pubkey;
  if (!OKhex.test(pubkey)) return res.send("Bad chars in pubkey");
  var email=req.query.email;
  var account=req.query.account;
  
  if (accounts[pubkey]) return res.send('Sorry, public key already registered');
  
  console.log("register "+email+"/"+account+" pubkey "+pubkey);
  accounts[pubkey]={
    "pubkey":pubkey,
    "email":email,
    "account":account,
    "balance":1000.0 //< universal basic income!
  };
  
  return res.send('Welcome '+email);
});

app.all('/roradora/balance', function(req, res) {
  var pubkey=req.query.pubkey;
  if (!OKhex.test(pubkey)) return res.send("Bad chars in pubkey");
  if (!accounts[pubkey]) return res.send('Unknown pubkey');
  
  return res.send(""+accounts[pubkey].balance);
});

app.all('/roradora/xfer', function(req, res) {
  var pubkey=req.query.pubkey;
  if (!OKhex.test(pubkey)) return res.send("Bad chars in source pubkey");
  var target=req.query.to;
  if (!OKhex.test(target)) return res.send("Bad chars in target address");
  var amount=req.query.amount;
  if (!OKhex.test(amount)) return res.send("Bad chars in amount");
  var signature=req.query.signature;
  if (!OKhex.test(signature)) return res.send("Bad chars in signature");
  
  var from=accounts[pubkey];
  var to=accounts[target];
  if (!from) return res.send('Unknown source pubkey');
  if (!to) return res.send('Unknown target pubkey');
  
  // FIXME: do sanity check, crypto check
  
  var amountFloat=parseInt(amount,16)/100.0; // starts as hex pennies
  from.balance -=amountFloat;
  to.balance +=amountFloat;
  
  return res.send("Transfer success!");
});

app.all('/roradora/dump', function(req, res) {
  var ret='<meta http-equiv="refresh" content="10">Account balances: <ul>';
  for (var pubkey in accounts) {
    var a=accounts[pubkey];
    ret+="<li>"+a.email+"/"+a.account+": "+a.balance+"£\n";
  }
  return res.send(ret);
});

app.listen(8888, function() {
  console.log('roradora app listening');
});


