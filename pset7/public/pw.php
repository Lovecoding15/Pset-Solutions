
 <?php
    // configuration


require("../includes/config.php");
// if form was submitted

if ($_SERVER["REQUEST_METHOD"] == "POST")
{
                $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);
                
                if (count($rows) == 1)
                {    
                     $row = $rows[0];
                }
                
        
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        
        if (empty($_POST["oldpassword"]))
        {
            apologize("You must provide the old password.");
        }
        
        if (empty($_POST["newpassword"]))
        {
            apologize("You must provide the new password.");
        }
        
        if (empty($_POST["confirmation"]))
        {
            apologize("You must provide the confirmation.");
        }
        
        if (crypt($_POST["oldpassword"], $row["hash"]) != $row["hash"])
        {
            apologize("Sorry, the old Password was not correct.");
        }
        

       if ($_POST["newpassword"] != $_POST["confirmation"])
        {
           apologize("Missmatch. The new passworddoes not match its Confirmation.");
        }
                
        else
        {
             if(query("UPDATE users SET hash = ( ? ) WHERE username = ( ? )", crypt($_POST["newpassword"]),$_POST["username"]) === false)
             
                  apologize("Sorry, some internal error ocured.");
             else
                  redirect("index.php");
            
        }
        
        
}  
else
{
    // else render form
    render("pw_form.php", ["title" => "Change Password"]);
}
?>
