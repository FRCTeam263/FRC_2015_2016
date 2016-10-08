import sys
import operator

'''
I am very sorry for the sloppy code.
Amd for the lack of the comments.
And for everything. 
This was written during a period of over 24 hours sans sleep in 20 mintues.
Any questions let me know.
'''
def main():
  file = sys.argv[1]
  if not file.endswith('.csv'):
    print "Only CSV files are supported, sorry. Please try again."
    sys.exit(0)
  defense_dict = {0: 'Portcullis', 1: 'Low Bar', 2: "Cheval de Frise", 3: "Moat", 4: "Ramparts", 5: "Sally Port", 6: "Draw Bridge", 7: "Rock Wall", 8: "Rough Terrain"}
  team1 = getInput()
  team2 = getInput()
  team3 = getInput()
  csv1 = getFromCSV(team1, file)
  csv2 = getFromCSV(team2, file)
  csv3 = getFromCSV(team3, file)
  defenses1 = getDefenses(csv1)
  defenses2 = getDefenses(csv2)
  defenses3 = getDefenses(csv3)
  defenses_master = map(operator.add, defenses1, defenses2)
  defenses_master = map(operator.add, defenses_master, defenses3)
  defenses = chooseTopThree(defenses_master)
  for defense in defenses:
    print defense_dict[defense]


def getInput():
  return input("Enter team:")

def getFromCSV(team_number, file):
  try:
    with open(file) as f:
      content = f.readlines()
  except IOError:
  	print "Invalid file. Please try again."
  	sys.exit(0)
  for line in content:
    if line.startswith(str(team_number)):
      return line
  print "Invalid team"
  sys.exit(0)

def getDefenses(csv):
  data = csv.split(',')
  data.pop(0)
  for i in range(len(data)):
    data[i] = 1 if data[i] == "No" or data[i] == "No\n" else 0
  return data

def chooseTopThree(defenses):
  return_list = []
  high_value = -1
  high_index = -1
  for i in range(len(defenses)):
    if defenses[i] > high_value:
      high_value = defenses[i]
      high_index = i
  return_list.append(high_index)
  defenses[high_index] = -1
  high_value = -1
  high_index = -1
  for i in range(len(defenses)):
    if defenses[i] > high_value:
      high_value = defenses[i]
      high_index = i
  return_list.append(high_index)
  defenses[high_index] = -1
  high_value = -1
  high_index = -1
  for i in range(len(defenses)):
    if defenses[i] > high_value and i != 6:
      high_value = defenses[i]
      high_index = i
  return_list.append(high_index)
  return return_list

if __name__ == '__main__':
	main()
