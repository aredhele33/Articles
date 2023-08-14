# String Identifier

The article was interesting ?
You can support me <a href="https://ko-fi.com/aredhele33">here</a>.

### What is the purpose of this project ?

This project provides sources to illustrate an article on https://vincentcalisto.com/

### What can I find in this project ?

A very simple implementation of a C++ compile time hash utility. You will find two utilities :

* SSID : 'Static'  utility to hash string at compile-time
* DSID : 'Dynamic' utility to hash string at runtime that relies on the same hash function

In a serious application, you might want to use at least CRC32 algorithm implementation but 
this one can be suitable for small personal projects.

### What is a string identifier in a few words ?

<div style="text-align: justify">
When dealing with a lot of strings, we likely want to avoid performing too much string
operations (such as char-by-char string comparison etc.), for performance purposes.
Instead, we can hash the strings to create a "unique" numbers from the character representation,
then we can use this number as an identifier to perform fast equality comparisons, for example. 
Sometimes, we already know the string value at compile time, so instead of wasting CPU cycles
to hash it dynamically at runtime, we can rely on C++ templates or constexpr/consteval features
to get this hash during compilation.
</div>

### How can I build this project ?

See instructions in the top README.md

### Contacts

* <a href="https://github.com/aredhele33/">GitHub</a>
* <a href="https://twitter.com/aredhele33">Twitter</a>
* <a href="https://www.linkedin.com/in/vincent-calisto/">LinkedIn</a>

Find all my contacts and socials <a href="https://vincentcalisto.com/me">here</a>
