<?php
$envVars = getenv();
$serverVars = $_SERVER;
?>
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Environment Variables</title>
  <style>
    header { text-align:center;}
  </style>
</head>
<body>
  <header><h1>PHP Environment Variables</h1><hr></header>
  <main>

    <h2>Environment Variables:</h2>
    <ul>
      <?php foreach ($envVars as $key => $value): ?>
        <li>
          <b><?= htmlspecialchars($key) ?></b>:
          <?= htmlspecialchars(is_array($value) ? json_encode($value) : (string)$value) ?>
        </li>
      <?php endforeach; ?>
    </ul>

    <h2>Server Variables</h2>
    <ul>
      <?php foreach ($serverVars as $key => $value): ?>
        <li>
          <b><?= htmlspecialchars($key) ?></b>:
          <?= htmlspecialchars(is_array($value) ? json_encode($value) : (string)$value) ?>
        </li>
      <?php endforeach; ?>
    </ul>
  </main>
</body>
</html>
