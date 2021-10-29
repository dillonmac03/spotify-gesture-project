import json
import spotipy
import spotipy.oauth2 as oauth2
import pprint
import os
import boto3
import time


# Access Token from environment variables ***********************************************
ACCESS_TOKEN = os.environ['ACCESS_TOKEN']

# Initialize Spotify Client API ****************************************

sp = spotipy.Spotify(auth=ACCESS_TOKEN)
client = boto3.client('sns')
arn = 'arn:aws:sns:us-west-1:979305578855:MySNS_Topic'

# Lambda Handler receives MQTT messages published to topic ******

def lambda_handler(event, context):
    
    
    gesture = event['gesture']
    if gesture == 'RIGHT':
        sp.next_track()
        #
        time.sleep(1)
        current_song = sp.current_user_playing_track()
        current_song = current_song['item']['name']
        
        # Publish to SNS
        response = client.publish(TargetArn=arn,
                                  Message= current_song,
                                  MessageStructure='raw')
    
        
    if gesture == 'LEFT':
        sp.previous_track()
        #
        time.sleep(1)
        current_song = sp.current_user_playing_track()
        current_song = current_song['item']['name']
        
        # Publish to SNS
        response = client.publish(TargetArn=arn,
                                  Message= current_song,
                                  MessageStructure='raw')
    if gesture == 'FAR':
        try:
            sp.pause_playback()
        except:
            sp.start_playback()
    
    
    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
