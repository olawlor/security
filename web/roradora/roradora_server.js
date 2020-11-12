/*
Node JS cryptocurrency server.
*/
var axlsign=require('./static/axlsign.js');
var roradora=require('./static/roradora.js');

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


// Add a "federal reserve" account to provide emergency liquidity
var fed={
        "pubkey":"0a5a4fc717d1b2348ea3a2e5236ff3fbf751693a3c3d053c3b2da104f5aeea11",
        "email":"reserve@fed.gov",
        "account":0,
        "id":"Federal Reserve",
        "balance":1000000000000.0
};
accounts[fed.pubkey]=fed;


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
    "id":email+"/"+account,
    "balance":100.0 //< universal basic income!
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
  
  // Check cryptographic signature
  var pubkeyBytes=roradora.bytesFromHex(pubkey);
  var signatureBytes=roradora.bytesFromHex(signature);
  console.log("Xfer: "+pubkeyBytes.length+" key, "+signatureBytes.length+" sig");
  var signedMessage=axlsign.openMessage(pubkeyBytes,signatureBytes);
  if (!signedMessage) return res.send("Invalid crypto in signature!");
  
  // Do the transfer
  var amountFloat=parseInt(amount,16)/100.0; // starts as hex pennies
  console.log("xfer "+amountFloat+" from "+from.id+" to "+to.id);
  from.balance -=amountFloat;
  to.balance +=amountFloat;
  
  return res.send("Transfer success!");
});

app.all('/roradora/dump', function(req, res) {
  var ret='<meta http-equiv="refresh" content="10">Account balances: <ul>';
  for (var pubkey in accounts) {
    var a=accounts[pubkey];
    ret+="<li>"+a.id+": "+a.balance+"£\n";
  }
  return res.send(ret);
});

app.listen(8888, function() {
  console.log('roradora app listening');
});


