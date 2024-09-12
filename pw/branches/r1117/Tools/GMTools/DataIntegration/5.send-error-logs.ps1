if (test-path logs\.failed*) {

  $from = 'brownie@nivalnetwork.com'
  $to = 'anton.prokofiev@nivalnetwork.com, eugene.ivanov@nivalnetwork.com'

  $message = New-Object Net.Mail.MailMessage($from, $to)
  $message.Subject = "Ошибки ETL"

  $message.Body = "Возникли ошибки при работе следующих инстансов ETL:`n"
  ls logs\.failed* |% {
    $message.Body += " - $($_.name.substring(8))`n"
    $file = cat $_
    if ((get-item $file).length -lt 5mb ) {
      $message.Attachments.Add($file)
    } else {
      $message.Body += "log file is too large to attach ($file)`n"
    }
    del $_
  }

  $smtp = New-Object Net.Mail.SmtpClient('edge1.nivalnetwork.com')
  $smtp.Send($message)
}
