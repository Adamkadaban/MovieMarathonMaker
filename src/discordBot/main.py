#!/bin/python3
import os
import sys
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
    user = str(message.author).split('#')[0]
    userMessage = str(message.content)
    channel = str(message.channel.name)

    # prevents bot from responding to itself
    if message.author == client.user:
        return

    if message.content.split()[0] == '!MovieMarathonMaker':
        if(message.content == "!MovieMarathonMaker"):
            await message.channel.send('```Need help?\n\tShow this menu:\n\t\t!MovieMarathonMaker -h\n\n\tMake a movie marathon:\n\t\t!MovieMarathonMaker <Actor 1> <Actor 2>\n\n\tShort on time?:\n\t\t!MovieMarathonMaker <Actor 1> <Actor 2> hurry```')
        


#token for server it runs in
client.run('OTE2ODM0ODczNTgxMzc1NTU5.Yav7Aw.mDNecNEjBhm34N_TRsnqlw27I1I')