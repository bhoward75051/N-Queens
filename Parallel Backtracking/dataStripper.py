from datetime import datetime


filename = 'testResults.txt'


#with open(filename) as file:
#    for line in file:
#        for value in line.split():
#            print(value)

matrix = []
seenValues = []
newTestResults = []
found = -1

with open(filename, 'r') as openfile:
    for line in openfile:
        matrix2 = line.split(" ")
        if int(matrix2[0]) == 0:
            matrix3 = [int(matrix2[1]), int(matrix2[2]), int(matrix2[3])]
            for j in range(0, len(seenValues)):
                if seenValues[j] == matrix3:
                    found = j

            pt = datetime.strptime(matrix2[4],'%M:%S.%f')
            total_seconds = pt.second + pt.minute*60

            if found < 0:
                seenValues.append(matrix3)

                newTestResults.append([int(matrix2[1]), int(matrix2[2]), int(matrix2[3]), int(total_seconds), int(round(float(matrix2[5])))])
            else:
                if newTestResults[found][3] > total_seconds:
                    newTestResults[found][3] = total_seconds
                    newTestResults[found][4] = int(round(float(matrix2[5])))
        found = -10
       
print(newTestResults)
openfile.close()
with open('newtestResults.txt', 'w') as f:
    for line in newTestResults:
        f.write(str(line[0]))
        f.write(" ")
        f.write(str(line[1]))
        f.write(" ")
        f.write(str(line[2]))
        f.write(" ")
        f.write(str(line[3]))
        f.write(" ")
        f.write(str(line[4]))
        f.write("\n")

f.close()
