from googleapiclient.http import MediaIoBaseDownload
from googleapiclient.errors import HttpError
from googleapiclient.discovery import build
from google.oauth2 import service_account
from termcolor import colored

from .Crendentials import drive_account
import io


def download_file(file_id: str, file_dst: str):
    
    try:
        credentials = service_account.Credentials.from_service_account_info(drive_account)
        service = build('drive', 'v3', credentials=credentials)
        request = service.files().get_media(fileId=file_id)
        file = io.BytesIO()
        downloader = MediaIoBaseDownload(file, request)
        done = False
        
        while done is False:
            status, done = downloader.next_chunk()
            print(colored("|    [Google]     ->", "green"), f" downloaded document : {file_id}")
        
    except HttpError as error:
        print(colored("|    [Google]     ->", "green"), colored(f" error downloading document : {file_id}", "red"))
        file = None

    dst = open(file_dst, "wb")
    dst.write(file.getvalue())
    dst.close()

def export_file(file_id: str, file_dst: str):
    
    try:
        credentials = service_account.Credentials.from_service_account_info(drive_account)
        service = build('drive', 'v3', credentials=credentials)
        request = service.files().export_media(fileId=file_id, mimeType='application/vnd.openxmlformats-officedocument.spreadsheetml.sheet')
        file = io.BytesIO()
        downloader = MediaIoBaseDownload(file, request)
        done = False
        
        while done is False:
            status, done = downloader.next_chunk()
            print(colored("|    [Google]     ->", "green"), f" downloaded document : {file_id}")
        
    except HttpError as error:
        print(colored("|    [Google]     ->", "green"), colored(f" error downloading document : {file_id}", "red"))
        file = None

    dst = open(file_dst, "wb")
    dst.write(file.getvalue())
    dst.close()