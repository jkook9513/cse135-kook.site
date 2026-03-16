<?php
date_default_timezone_set("America/Los_Angeles");

$method = $_SERVER["REQUEST_METHOD"] ?? "GET";
$ct = $_SERVER["CONTENT_TYPE"] ?? "";
$ip = $_SERVER["REMOTE_ADDR"] ?? "unknown";
$ua = $_SERVER["HTTP_USER_AGENT"] ?? "unknown";
$host = gethostname();
$time = date("c");

$raw = file_get_contents("php://input");
$query = $_GET;

$body_parsed = null;
if ($method !== "GET" && strlen($raw) > 0) {
  if (stripos($ct, "application/json") !== false) {
    $body_parsed = json_decode($raw, true);
  } elseif (stripos($ct, "application/x-www-form-urlencoded") !== false) {
    if ($method === "POST") $body_parsed = $_POST;
    else { $tmp = []; parse_str($raw, $tmp); $body_parsed = $tmp; }
  }
}

header("Content-Type: application/json");
echo json_encode([
  "language" => "php",
  "hostname" => $host,
  "time" => $time,
  "ip" => $ip,
  "user_agent" => $ua,
  "method" => $method,
  "content_type" => $ct,
  "query" => $query,
  "body" => $body_parsed,
  "raw" => $raw
], JSON_PRETTY_PRINT);
