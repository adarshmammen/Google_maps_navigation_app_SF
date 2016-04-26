import xml.etree.cElementTree as ET

with open('cal_cnode.txt') as f_nodes_to_latlong:
    content = f_nodes_to_latlong.readlines()

#print(content[20]);
f = open('neigh_node.txt', 'r')




line1 = f.readline()


line2 = f.readline()


line3 = f.readline()


line4 = f.readline()


line5 = f.readline()



root = ET.Element("root")
#1st shortest path

if line1:
	doc = ET.SubElement(root, "row")
	latlong = content[int(line1)].split(' ')
	ET.SubElement(doc, "lat").text = latlong[2]
	ET.SubElement(doc, "long").text = latlong[1] # may have to switch

#2nd shortest path
if line2:
	doc = ET.SubElement(root, "row")
	latlong = content[int(line2)].split(' ')
	ET.SubElement(doc, "lat").text = latlong[2]
	ET.SubElement(doc, "long").text = latlong[1] # may have to switch


if line3:
	doc = ET.SubElement(root, "row")
	latlong = content[int(line3)].split(' ')
	ET.SubElement(doc, "lat").text = latlong[2]
	ET.SubElement(doc, "long").text = latlong[1] # may have to switch

#2nd shortest path
if line4:
	doc = ET.SubElement(root, "row")
	latlong = content[int(line4)].split(' ')
	ET.SubElement(doc, "lat").text = latlong[2]
	ET.SubElement(doc, "long").text = latlong[1]

if line5:
	doc = ET.SubElement(root, "row")
	latlong = content[int(line5)].split(' ')
	ET.SubElement(doc, "lat").text = latlong[2]
	ET.SubElement(doc, "long").text = latlong[1]

tree = ET.ElementTree(root)
tree.write("latlong.xml")
#3rd shortest path


#print(mylist1[:-1])
#print('\n')
#rint(mylist2[:-1])
#print('\n')
#print(mylist3[:-1])

f.close()