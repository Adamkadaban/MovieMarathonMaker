# bot.py
import os

import discord
from dotenv import load_dotenv

load_dotenv()
TOKEN = os.getenv('OTE2ODM0ODczNTgxMzc1NTU5.Yav7Aw.mDNecNEjBhm34N_TRsnqlw27I1I')

client = discord.Client()
@client.event
async def on_ready():
    print(f'{client.user} has connected to Discord!')

@client.event
async def on_member_join(member):
    await member.create_dm()
    await member.dm_channel.send(
        f'Hi {member.name}, welcome to my Discord server!'
    )

@client.event
async def on_message(message):

    if message.author == client.user:
        return

    if message.content == 'MovieMarathon':
        await message.channel.send('Calculating...')


#token for server it runs in
client.run('OTE2ODM0ODczNTgxMzc1NTU5.Yav7Aw.mDNecNEjBhm34N_TRsnqlw27I1I')