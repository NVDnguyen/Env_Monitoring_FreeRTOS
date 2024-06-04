#ifndef WEB_H
#define WEB_H

const char *html = R"rawliteral(<!DOCTYPE html>
<html>
<head>
<title>WiFi Setup</title>
<style>
body {
    font-family: sans-serif;
    display: flex;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
    background-color: #f0f0f0;
}
form {
    background-color: white;
    padding: 30px;
    border-radius: 8px;
    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
}
label {
    display: block;
    margin-bottom: 8px;
}
input[type="text"],
input[type="password"] {
    width: 100%;
    padding: 10px;
    margin-bottom: 15px;
    border: 1px solid #ccc;
    border-radius: 4px;
    box-sizing: border-box;
}
input[type="submit"] {
    background-color: #4CAF50;
    color: white;
    padding: 12px 20px;
    border: none;
    border-radius: 4px;
    cursor: pointer;
}
input[type="submit"]:hover {
    background-color: #45a049;
}
</style>
</head>
<body>

<form action="/save" method="post">
    <h2>WiFi Setup</h2>
    <label for="ssid">SSID:</label>
    <input type="text" id="ssid" name="ssid"><br><br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Save">
</form>

</body>
</html>
)rawliteral";

#endif
