<?php
    include "config.php";

    session_start();

    if($_GET["Login"] == "True") {
        $sPassword = $_POST["Password"];
        if($sPassword == $cPassword) $_SESSION["Login"] = "OK";
    }

    if($_GET["Login"] == "False") {
        session_destroy();
        header("Location: index.php");
    }
?>

<html>

<head>
    <title>Slides</title>
    <meta Http-Equiv="Content-Type" Content="text/html; charset=UTF-8" />
</head>

<style Type="text/css">
    .Body         {Background: #FFFFFF;}
    .Box          {Margin: 120px auto 0 auto; Border: 0;}
    .Text, .Header, .Footer
                  {Color: #000000; Font-Family: Sans-Serif;}
    .Text a       {Color: #000000; Text-Decoration: None;}
    .Text a:hover {Color: #0000FF; Text-Decoration: None;}
    .Text         {Padding: 8px; Font-Size: 20px; Text-Align: Left;}
    .Header       {Padding-Bottom: 4px; Font-Weight: Bold; Font-Size: 30px; Text-Align: Center; Border-Bottom: 1px Solid #333333;}
    .Footer       {Padding-Top: 4px; Font-Size: 18px; Text-Align: Center; Border-Top: 1px Solid #333333;}
    .Text input   {Background-Color: #FFFFFF; Color: #000000; Border: 1px Solid #333333; Text-Align: Center; Border-Radius: 4px; Padding: 4px;}
</style>

<script Type="text/javascript">
    function setFocus() {
        document.Form.Password.focus();
    }
</script>

<body Class="Body" OnLoad='setFocus()'>
    <table Class="Box">
        <tr><td Class="Header">Slides</td></tr>
        <tr>
            <td Class="Text">
                <?php
                    if($_SESSION["Login"] == "OK" || $cPassword == "") {
                        $aPresentations = array();
                        foreach(scandir("presentations") as $sObject) {
                            if(is_dir("presentations/".$sObject) && substr($sObject, 0, 1) != ".") {
                                include "presentations/".$sObject."/config.php";
                                $aPresentations[strtotime($sPresentationDate)] = array("Title"=>$sPresentationTitle, "Path"=>$sObject);
                            }
                        }
                        ksort($aPresentations);
                        foreach($aPresentations as $sDate=>$aData) {
                            echo "&raquo;&nbsp;&nbsp;<a Href='presentations/".$aData["Path"]."/'>";
                                echo date("d.m.Y", $sDate)." &ndash; ".$aData["Title"];
                            echo "</a><br>".chr(10);
                        }
                    } else {
                        echo "<form Name='Form' Method='Post' Action='?Login=True'>";
                        echo "Password:&nbsp;<input Type='Password' Name='Password'>";
                        echo "</form>".chr(10);
                    }
                ?>
            </td>
        </tr>
        <?php if($_SESSION["Login"] == "OK" || $cPassword == "") { ?>
            <tr><td Class="Footer"><a Href="index.php?Login=False">Logout</a></td></tr>
        <?php } ?>
    </table>
</body>

</html>
