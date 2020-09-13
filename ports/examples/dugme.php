<?php
        system("gpio mode 0 input");
        exec("gpio read 0", $sonuc);

        if ($sonuc[0] == 1)
                echo "Butona basili.";
        else
                echo "Buton basili degil.";
?>
