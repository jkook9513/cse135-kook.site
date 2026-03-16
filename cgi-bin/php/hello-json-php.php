<?php
    date_default_timezone_set("America/Los_Angeles");
    header("Content-Type: application/json");

    $date = date("Y-m-d H:i:s.T");
    $address  = $_SERVER['REMOTE_ADDR'] ?? 'unknown';

    $data = [
        "title" => "Hello, PHP!",
        "message" => "Hello World from Team Kook! This page was generated with the Python programming language.",
        "time" => $date,
        "ipAddress" => $address
    ];

    echo json_encode($data)
    
?>