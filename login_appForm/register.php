<?php
	session_start();
	
	// initializing variables
	$email = "";
	$fullname = "";
	$username = "";
	$errors = array(); 
	
	// connect to the database
	$db = mysqli_connect('localhost', 'root', '', 'myapp');
	
	// LOGIN USER
	if (isset($_POST['login_user'])) {
		//Redirect to login.php
		header('location: login.php');
	}

	// REGISTER USER
	if (isset($_POST['reg_user'])) {
		// receive all input values from the form
		$email = mysqli_real_escape_string($db, $_POST['email']);
		$fullname = mysqli_real_escape_string($db, $_POST['fullname']);
		$username = mysqli_real_escape_string($db, $_POST['username']);
		$password = mysqli_real_escape_string($db, $_POST['password']);


		// form validation: ensure that the form is correctly filled ...
		// by adding (array_push()) corresponding error unto $errors array
		if (!(preg_match('/^[a-zA-Z0-9]+$/', $username))) { array_push($errors, "Username must be English letter or numeric"); }
		if (!(preg_match('/^[a-zA-Z0-9]+$/', $password))) { array_push($errors, "Password must be English letter or numeric"); }
		if ((strlen($email) < 8) or (strlen($email) > 30)) { array_push($errors, "Email must be greater than 8 or less than 30"); }
		if ((strlen($fullname) < 8) or (strlen($fullname) > 30)) { array_push($errors, "Fullname must be greater than 8 or less than 30"); }
		if ((strlen($username) < 6) or (strlen($username) > 20)) { array_push($errors, "Username must be greater than 6 or less than 20"); }
		if ((strlen($password) < 6) or (strlen($password) > 20)) { array_push($errors, "Password must be greater than 6 or less than 20"); }
		
		// check redundant username
		$user_check = "SELECT username FROM users";
		$result = mysqli_query($db, $user_check);
		if (mysqli_num_rows($result) > 0){
			// output data of each row
			while($row = mysqli_fetch_assoc($result)){
				if ($username == $row["username"]){
					array_push($errors, "Username already exists");						
				} 
			}
		}


		// If no error, add data into database
		if (count($errors)==0){
			$query = "INSERT INTO users (username, password, fullname) VALUES('$username', MD5('$password'), '$fullname' )";
			mysqli_query($db, $query);

			//Add to session variables
			$_SESSION['username'] = $username;
			$_SESSION['fullname'] = $fullname;
			$_SESSION['loggedin'] = True;

			//Redirect to login.php
			header('location: login.php');
		}

	}
?>

<html>

<head>
  <title>Registration</title>
  <link rel="stylesheet" href="css/style.css">
</head>

<body style="backgroud-color:#7f8c8d">
	<h1>Smart Fram (IOT)</h1>
	<div id="main-wrapper">
		<center>
		<h2>Register Form</h2>
		<p><img src="img/msn.png" width="100" class="msn"/></p>
		</center>
		
		<form action=""register.php method="post">
			<center>
			<label>Email</label><br>
			<p><input type="text" class="inputvalues" name="email" value="<?php echo $email; ?>"><br></p>
			<label>Fullname</label><br>
			<p><input type="text" class="inputvalues" name="fullname" value="<?php echo $fullname; ?>"><br></p>
			<label>Username</label><br>
			<p><input type="text" class="inputvalues" name="username" value="<?php echo $username; ?>"><br></p>
			<label>Password</label><br>
			<p><input type="password" class="inputvalues" name="password"><br></p>
			<p><button type="submit" class="register_btn" name="reg_user">Sign Up</button></p>
			</center>
			<p><a href="login.php">Back to login from</a></p>
		</form>
	</div>
	



<?php  if (count($errors) > 0) : ?>
  <hr/>
  <ul style="color:red;">
  	<?php foreach ($errors as $error) : ?>
  	  <li><?php echo $error ?></li>
  	<?php endforeach ?>
  </ul>
<?php  endif ?>


</body>
</html>
