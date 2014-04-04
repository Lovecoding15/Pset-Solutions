<table class="table table-bordered">

    <thead>
        <tr>
            <th>Transaction Type</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>


    <tbody align="left">
    <?php
            foreach ($table as $row)    
        {   
            echo("<tr>");
            echo("<td>" . $row["transaction"] . "</td>");
            echo("<td>" . date('d/m/y, g:i A',strtotime($row["date"])) . "</td>");
            echo("<td>" . $row["symbol"] . "</td>");
            echo("<td>" . $row["shares"] . "</td>");
            echo("<td>$" . number_format($row["price"], 2) . "</td>");
            echo("</tr>");
        }
    ?>

    <tr>
        <td class="hello" colspan="4"><strong>CASH</strong></td>
        <td class="hello"><strong>$<?=number_format($cash[0]["cash"], 2)?></strong></td>
    </tr>

    </tbody>
    
</table>
