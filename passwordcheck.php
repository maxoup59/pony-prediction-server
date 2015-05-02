
<?php
    if(isset($_POST["password"]) && isset($_POST["hash"]))
    {
        if(password_verify ( $_POST["password"], $_POST["hash"] ))
       {
           echo "true";
       }
       else
       {
           echo "false";
       }
    }
    else
    {
       echo "false";
    }
?>