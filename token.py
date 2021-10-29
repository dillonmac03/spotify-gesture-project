import json
import os
import time

import spotipy
import spotipy.util as util
from pprint import pprint

SPOTIPY_CLIENT_ID = ''
SPOTIPY_CLIENT_SECRET = ''
SPOTIPY_USER = ''
SPOTIPY_REDIRECT_URI = 'http://localhost/'


scope = "user-read-playback-state user-modify-playback-state"

util.prompt_for_user_token(
    username=SPOTIPY_USER,
    scope=scope,
    client_id=SPOTIPY_CLIENT_ID,
    client_secret=SPOTIPY_CLIENT_SECRET,
    redirect_uri=SPOTIPY_REDIRECT_URI)

with open('./.cache-'+SPOTIPY_USER) as f:
    data = json.load(f)
pprint(data)



print("Stored token")

    

