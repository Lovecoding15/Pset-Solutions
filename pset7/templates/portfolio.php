
    <?php
        $user = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        printf("<p class=\"hello\"><br/>Hello <strong>%s</strong>.   -   Your balance is at <strong>%.4f $</strong>.</p>",$user [0]['username'], $user [0]['cash']);
      
    ?>   
      
<table class="table table-bordered">

    <thead>
        <tr>
            <th>    Symbol  </th>
            <th>    Name    </th>
            <th>    Shares  </th>
            <th>    Price   </th>
            <th>    TOTAL   </th>
        </tr>
    </thead>

    <tbody align="left">
    
    <?php
            foreach ($portfolio as $row)        
        {   
            echo("<tr>");
            echo("<td>" . $row["symbol"] . "</td>");
            echo("<td>" . $row["name"] . "</td>");
            echo("<td>" . $row["shares"] . "</td>");
            echo("<td>$" . number_format($row["price"], 4) . "</td>");
            echo("<td>$" . number_format($row["total"], 4) . "</td>");
            echo("</tr>");
        }
    ?>
       
    </tbody>
    
</table>
  





