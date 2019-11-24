<?php

 /*   switch ($_SERVER['SERVER_NAME']) {   
            
        default:
        case 'smartfarmpi.host.imakeservice.com':
            $Configs["SERVER"] = 'db.imakeservice.com';
            $Configs["USERNAME"] = 'smartfarmpi';
            $Configs["PASSWORD"] = 'iMakeProject';
            $Configs["DATABASE"] = 'smartfarmpi';
            if (!isset($Configs["DEBUG"]))
            $Configs["DEBUG"] = true;
        break;*/
            

                    
            $Configs["USERNAME"] = 'root';
            $Configs["PASSWORD"] = '';
			$configs["host"] = 'localhost';
            $Configs["DATABASE"] = 'smartfarmpi';
            $Configs["DEBUG"] = true;



    require_once('core/init.php');
    require_once('appdata.php');

    $User_Id = intval( $_COOKIE['user_id'] );
    if ($User_Id > 0)
    {
        $User = DynDb_SelectTable("SELECT * FROM users WHERE user_id = {$User_Id}", true);
        if (count($User) <= 0)
        {
            $User = null;
            $User_Id = 0;
        }
        else
        {
            $IsAdmin = ($User['user_type'] == 'admin');
            $IsUser = (($User['user_type'] == 'user') || ($User['user_type'] == '')) ;
            $IsManager = (!$IsUser);
        }
    }

    $Title = "ระบบจัดการ SmartFarm";
    
?>