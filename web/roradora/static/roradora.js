(function(roradora) {
"use strict"; 
/*
  Load cryptocurrency code.
*/

console.log("Loading roradora");

if (typeof process==='object') { // probably node.js
    console.log("Bringing in node js TextEncoder");
    var util= require('util');
    global.TextEncoder = util.TextEncoder;
    global.TextDecoder = util.TextDecoder;
}

var utf8e=new TextEncoder();
var utf8d=new TextDecoder();

// Conversions between strings, Uint8Arrays, base64, and hex.
// Convert a UTF-8 string to a Uint8Array, byte by byte
roradora.bytesFromString=function(str) {
    return utf8e.encode(str);
};

// Convert a Uint8Array to a UTF-8 string, byte by byte
roradora.stringFromBytes=function(msg) {
    return utf8d.decode(msg);
};

// Hash a UTF-8 string to a 64-byte array via SHA-512
roradora.hash64b=function(str) {
    return axlsign.sha512(roradora.bytesFromString(str));
};

// Hash a UTF-8 string to a 32-byte array
roradora.hash32b=function(str) {
    return roradora.hash64b(str).slice(0,32);
};

// Convert a Uint8Array to a base64 string
roradora.base64FromBytes=function(byteArray) {
    return btoa(String.fromCharCode.apply(null, byteArray));
};
// Convert base64 to a Uint8Array
roradora.bytesFromBase64=function(base64str) {
    return Uint8Array.from(atob(base64str), c=>c.charCodeAt(0));
};

// Return a two-char hex string for this byte value
roradora.hexFromByte=function(byte) {
    var str=byte.toString(16);
    str=(str.length<2)?'0'+str:str; // add leading 0
    return str;
};

// Return an all-hex string view of this byte array
roradora.hexFromBytes=function(byteArray) {
    return byteArray.reduce(
        function(str, i) {return str + roradora.hexFromByte(i)},
        ''
    );
};
// Return a byte array Uint8Array from an all-hex string
roradora.bytesFromHex=function(string) {
    var arr=new Uint8Array(string.length/2);
    for (var b=0;b<arr.length;b++)
        arr[b]=parseInt(string.substr(b*2,2),16);
    return arr;
};

// Debug-print this byteArray to the console:
roradora.debug=function(what,byteArray) {
    console.log(what+roradora.hexFromBytes(byteArray));
};


})(typeof module !== 'undefined' && module.exports ? module.exports : (self.roradora = self.roradora || {}));


