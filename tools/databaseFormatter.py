#!/bin/python3
'''
Note: This only returns what is listed as a "movie" on the IMDB database
	  Unfortunately, there are some mistakes on the db. 

	  Example: Harry Potter and the Sorcerer's Stone is listed as "tvEpisode"

	  Some minor characters will also be excluded

'''

import csv
actorToMovies = csv.reader(open('resources/name.basics.tsv'), delimiter="\t")
movieIDToInfo = csv.reader(open('resources/title.basics.tsv'), delimiter="\t")
#titleAKAs = csv.reader(open('resources/title.akas.tsv'), delimiter="\t")
actorIDToActor = csv.reader(open('resources/title.principals.tsv'), delimiter="\t")


# exclude first line in file (which is the table header) 
next(actorToMovies)
next(movieIDToInfo)
next(actorIDToActor)



def getMovies(actor):
	actorIDs = []

	for i in actorToMovies:
		if(i[1] == actor):
			ActorIDs.append((i[0], len(i[5].split(","))))

	# ActorIDs.sort(key = lambda x: x[1], reverse=True)

	topActorID = max(actorIDs, key = lambda x: x[1])

	titles = set()
	for i in actorIDToActor:
		if(i[2] == topActorID):
			titles.add(i[0])

	outs = []
	for i in movieIDToInfo:
		if(i[0] in titles and i[1] == "movie"):
			outs.append(i[2])

	return outs



# movie, length, all actors
data = []


# Adding all movies 
for line in movieIDToInfo:
	# data for filtering
	movieType = line[1]
	runtime = line[7]

	if(movieType == "movie" and runtime != "\\N" ):
		movieID = line[0]
		year = line[5]
		movieName = line[2]
		
		if(year != "\\N"):
			movieName += " (" + str(year) + ")"

		
		# movie ID, movie Title, Movie runtime, actorIDs
		temp = [movieID, movieName, runtime, []]
		data.append(temp)


# generate relations between movie ID and actor IDs
movieIDtoActors = {}
for line in actorIDToActor:
	titleID = line[0]
	actorID = line[2]

	if(titleID not in movieIDtoActors):
		movieIDtoActors[titleID] = [actorID]
	else:
		movieIDtoActors[titleID].append(actorID)


# add actor IDs to each movie


c = 0
for movie in data:
	movieID = movie[0]
	actors = movie[3]
	try:
		actors.extend(movieIDtoActors[movieID])
	except:
		c += 1


actorIDstoActors = {}
for line in actorToMovies:
	actorID = line[0]
	actorName = line[1]

	actorIDstoActors[actorID] = actorName



for movie in data:
	actorIDs = movie[3]

	actors = []

	for i in actorIDs:
		try:
			actors.append(actorIDstoActors[i])
		except:
			pass

	actorIDs.clear()
	actorIDs.extend(actors)
	

# print(data[0])

with open('Database.tsv', 'w') as fout:
	for line in data:
	  temp = line[-1]
	  del line[-1]
	  line.extend(temp)

	  del line[0]

	  fout.write("\t".join(line) + '\n')

