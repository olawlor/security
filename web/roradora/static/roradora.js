/*
  Load cryptocurrency code.
*/
"use strict"; // this is ES6 code

console.log("Loading roradora");

var utf8e=new TextEncoder('utf-8');
var utf8d=new TextDecoder('utf-8');

// All of these functions can be accessed from "rora."
window.rora={

// Conversions between strings, Uint8Arrays, base64, and hex.
    // Convert a UTF-8 string to a Uint8Array, byte by byte
    bytesFromString:function(str) {
        return utf8e.encode(str);
    },
    
    // Convert a Uint8Array to a UTF-8 string, byte by byte
    stringFromBytes:function(msg) {
        return utf8d.decode(msg);
    },
    
    // Hash a UTF-8 string to a 64-byte array via SHA-512
    hash64b:function(str) {
        return axlsign.sha512(rora.bytesFromString(str));
    },

    // Hash a UTF-8 string to a 32-byte array
    hash32b:function(str) {
        return rora.hash64b(str).slice(0,32);
    },
    
    // Convert a Uint8Array to a base64 string
    base64FromBytes:function(byteArray) {
        return btoa(String.fromCharCode.apply(null, byteArray));
    },
    // Convert base64 to a Uint8Array
    bytesFromBase64:function(base64str) {
        return Uint8Array.from(atob(base64str), c=>c.charCodeAt(0));
    },
    
    // Return a two-char hex string for this byte value
    hexFromByte:function(byte) {
        var str=byte.toString(16);
        str=(str.length<2)?'0'+str:str; // add leading 0
        return str;
    },
    
    // Return an all-hex string view of this byte array
    hexFromBytes:function(byteArray) {
        return byteArray.reduce(
            function(str, i) {return str + rora.hexFromByte(i)}, 
            ''
        );
    },
    // Return a byte array Uint8Array from an all-hex string
    bytesFromHex:function(string) {
        var arr=new Uint8Array(string.length/2);
        for (var b=0;b<arr.length;b++)
            arr[b]=parseInt(string.substr(b*2,2),16);
        return arr;
    },
    
    // Debug-print this byteArray to the console:
    debug:function(what,byteArray) {
        console.log(what+rora.hexFromBytes(byteArray));
    },

};




