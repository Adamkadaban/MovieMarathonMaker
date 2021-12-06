#!/bin/python3
import os
import sys
import discord
from dotenv import load_dotenv



# sets working directory to source directory
os.chdir('..')

def getParams(s):
    r = s.split('" "')
    firstPart = r[0].split(' "')
    lastPart = r[1].split('" ')
    if(len(lastPart) == 1):
        lastPart[0] = lastPart[0][:-1]
    r = firstPart + lastPart
    print(r)
    return r

def help():
    return 'Make a Movie Marathon™ to go from any actor to another!\n\nNeed help?\n\tShow this menu:\n\t\t!MovieMarathonMaker -h\n\n\tMake a movie marathon:\n\t\t!MovieMarathonMaker "<Actor 1>" "<Actor 2>"\n\n\tShort on time?:\n\t\t!MovieMarathonMaker "<Actor 1>" "<Actor 2>" hurry\n\n\tReally short on time?:\n\t\t!MovieMarathonMaker "<Actor 1>" "<Actor 2>" super hurry\n\n\tCompare all algorithms:\n\t\t!MovieMarathonMaker "<Actor 1>" "<Actor 2>" compare'
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

    if message.content.split()[0] == '!MovieMarathonMaker' or message.content.split()[0] == "!MM":
        if(message.content == "!MovieMarathonMaker" or message.content == "!MM" or "-h" in message.content.split()) :
            await message.channel.send("```"+help()+"```")
        ins = getParams(message.content)
        fro = ins[1]
        to = ins[2]
        if(len(ins) == 3):
            output = os.popen(f'./main "{fro}" dijkstra "{to}"').read()
            await message.channel.send(f'```{output}```')
        elif(ins[3] == "hurry"):
            output = os.popen(f'./main "{fro}" aStar "{to}"').read()
            await message.channel.send(f'```{output}```')
        elif(ins[3] == "super hurry"):
            output = os.popen(f'./main "{fro}" movieStar "{to}"').read()
            await message.channel.send(f'```{output}```')
        elif(ins[3] == "compare"):
            output = os.popen(f'./main "{fro}" compare "{to}"').read()
            await message.channel.send(f'```{output}```')
        else:
            await message.channel.send(f'```I don\'t know what **{ins[3]}** means\n{help()}```')


#token for server it runs in
client.run('OTE2ODM0ODczNTgxMzc1NTU5.Yav7Aw.mDNecNEjBhm34N_TRsnqlw27I1I')