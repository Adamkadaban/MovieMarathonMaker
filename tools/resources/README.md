# File Retrieval
* All files from [IMDbDatasets](https://datasets.imdbws.com/)
### Automatic
* Run the following command: `./getFiles`
	* This will download/update and extract all necessary files

### Manual
* Download and gunzip the following and place into this folder:
	* [name.basics.tsv](https://datasets.imdbws.com/name.basics.tsv.gz)
	* [title.basics.tsv](https://datasets.imdbws.com/title.basics.tsv.gz)
	* [title.akas.tsv](https://datasets.imdbws.com/title.akas.tsv.gz)
	* [title.principals.tsv](https://datasets.imdbws.com/title.principals.tsv.gz)

* Unzip the files by runnnig:
	* `gunzip *.gz`

# Database building
* In `src/tools/`, run `./databaseBuilder.py`
