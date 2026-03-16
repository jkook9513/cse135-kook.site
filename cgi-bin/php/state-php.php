<?php
session_start();

if (isset($_POST["name"]) && $_POST["name"] !== "") {
    $_SESSION["name"] = $_POST["name"];
}

// optional clear
if (isset($_GET["clear"])) {
    session_unset();
    session_destroy();
    header("Location: state-php.php");
    exit;
}

$name = $_SESSION["name"] ?? "(nothing set yet)";
?>
<!doctype html>
<html>
<head><meta charset="utf-8"><title>State (PHP)</title></head>
<body>
  <h1>State Page (PHP)</h1>
  

  <p><b>Saved name:</b> <?= htmlspecialchars($name) ?></p>

  <p>
    <a href="/session/php-cgiform.html">Back to form</a> |
    <a href="/index.html">Home</a> |
    <a href="state-php.php?clear=1">Clear</a>
  </p>
</body>
</html>
