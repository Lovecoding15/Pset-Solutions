


<form action="pw.php" method="post">
    <fieldset>
        <div class="form-group">
            
            <input name="username" value= 
            
            <?php 
            $user = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
                        echo ($user [0]['username']);
                        ?>
                   
                       type="text"/>
              
        </div>
        <div class="form-group">
            <input autofocus name="oldpassword" placeholder="Old Password" type="password"/>
        </div>
        <div class="form-group">  
            <input name="newpassword" placeholder="New Password" type="password"/>
         </div>
        <div class="form-group">   
            <input name="confirmation" placeholder="Confirmation" type="password"/>
        </div>
        
        <div class="form-group">
                        <button type="submit" class="btn btn-default">Register!</button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="logout.php">Logout!</a>
</div>
