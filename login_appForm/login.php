<?php session_start(); 
// initializing variables
$username = "";
$email    = "";
$errors = array(); 

// connect to the database
$db = mysqli_connect('localhost', 'root', '', 'myapp');
 // LOGIN USERs
if (isset($_POST['login_user'])) {
  $username = mysqli_real_escape_string($db, $_POST['username']);
  $password = mysqli_real_escape_string($db, $_POST['password']);

  if (empty($username)) {
    array_push($errors, "Username is required");
  }
  if (empty($password)) {
    array_push($errors, "Password is required");
  }

  if (count($errors) == 0) {
    $password = md5($password);
    $query = "SELECT * FROM users WHERE username='$username' AND password='$password'";
    $results = mysqli_query($db, $query);
    if (mysqli_num_rows($results) == 1) {
      $_SESSION['username'] = $username;
      $_SESSION['success'] = "You are now logged in";
      header('location: home.php');
    }else {
      array_push($errors, "Wrong username/password combination");
    }
  }
}
?>
<!DOCTYPE html>
<html>
<head>
  <title>login_user</title>
  <link rel="stylesheet" href="css/style.css">
</head>

<body style="backgroud-color:#7f8c8d">
	<h1>Smart Fram (IOT)</h1>
	<div id="main-wrapper">
		<center>
		<h2>Login Form</h2>
		<p><img src="img/msn.png" width="100" class="msn"/></p>
		</center>
	 
		<form action=""login.php method="post">
			<center>
			<label>Username</label>
			<p><input type="text" name="username" class="inputvalues"><br></p>
			<label>Password</label>
			<p><input type="password" name="password" class="inputvalues"></p>
			<p><button type="submit" class="btn" name="login_user">Login</button></p>
			</center>
			<p><a href="register.php">Go to register from</a></p>
	  </form>
</body>

</html>
