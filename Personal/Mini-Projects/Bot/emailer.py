from config import EMAIL_HOST, EMAIL_PORT, EMAIL_USER, EMAIL_PASS, EMAIL_TO
from email.message import EmailMessage
import smtplib

def send_email(subject, html_blob):
    msg = EmailMessage()
    msg["From"] = EMAIL_USER
    msg["To"] = EMAIL_TO
    msg["Subject"] = subject
    msg.add_alternative(html_blob, subtype="html")

    with smtplib.SMTP(EMAIL_HOST, EMAIL_PORT) as s:
        s.starttls()
        s.login(EMAIL_USER, EMAIL_PASS)
        s.send_message(msg)
        print("✅ Email sent.")
