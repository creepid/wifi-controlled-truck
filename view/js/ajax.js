function ajaxSend(param)
{
     $.ajax({
          type: "GET",
          url: "http://192.168.1.1/serial.php",
          data: "comm=" + param
     });
}