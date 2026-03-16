<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hello HTML World</title>
    <style>
            header { text-align:center;}
    </style>
</head>
<body>
    <header><h1>PHP Hello World!</h1><hr></header>
    <main>
        <?php
            date_default_timezone_set("America/Los_Angeles");
            $address  = $_SERVER['REMOTE_ADDR'] ?? 'unknown';
            $date = date("Y-m-d H:i:s.T");
            echo "<p>Hello World from Team Kook!</p>";
            echo "<p>This page was generated with the PHP programming language.</p>";
            echo "<p>Today's date is: $date</p>";
            echo "<p>Your current IP address is: $address</p>";
        ?>
    </main>
    
</body>
</html>