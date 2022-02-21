#Script to retrieve the results from a set of crab jobs and merge component job outputs together


import os
import sys

#---------------------------------------------------------------------------------------------------------------------

#Given an (optional directory prototype, returns a list of directories in crab_projects/ matching that prototype
def getProjDirs(dirPrototype = ""):
	dirs = next(os.walk('../crab/crab_projects/'))[1] #Get all project directories
	dirs = [dir for dir in dirs if dir.startswith(dirPrototype)] #Reduce to only dirs of interest
	return dirs

#---------------------------------------------------------------------------------------------------------------------

#Retrieves the results of the projects in dirs
def getResults(dirs):
	for dir in dirs:
		os.system("crab getoutput -d ../crab/crab_projects/" + dir)

#---------------------------------------------------------------------------------------------------------------------

#Merge the results of each project into a single root file
def mergeResults(dirs, removeOriginals = False):
	for dir in dirs:
		path = "../crab/crab_projects/" + dir + "/"
		inputs = next(os.walk(path + "results/"))[2]
		if len(inputs) <= 1:
			print "No merging required for project " + dir
			continue 
		inputs_string = ""
		for input in inputs:
			inputs_string += " " + path + "results/" + input
		outputName = dir[5].lower() + dir[6:] + ".root" #Remove crab_ and make first letter lowercase 
		os.system("python haddnano.py " + outputName + inputs_string) #Use haddnano.py to merge root files
 		os.system("mv " + outputName + " " +  path + "results/")  
	
		if removeOriginals:
			os.system("rm" + inputs_string)

#---------------------------------------------------------------------------------------------------------------------

def main(argv):
	dirProto = argv[1]
	dirs = getProjDirs(dirProto)
	getResults(dirs)
	mergeResults(dirs)

#---------------------------------------------------------------------------------------------------------------------

if __name__ == "__main__":
	if len(sys.argv) < 2 or len(sys.argv) > 3:
		print "Usage: python outputMerge.py <prototype directory name> <OP: removeOriginals = False>"
	else:
		main(sys.argv) 
