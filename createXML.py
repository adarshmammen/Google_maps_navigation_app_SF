import xml.etree.cElementTree as ET

with open('cal_cnode.txt') as f_nodes_to_latlong:
    content = f_nodes_to_latlong.readlines()

#print(content[20]);
f = open('nodes_for_xml.txt', 'r')

line1 = f.readline()
mylist1 = line1.split(",")

line2 = f.readline()
mylist2 = line2.split(",")

line3 = f.readline()
mylist3 = line3.split(",")


root = ET.Element("root")


for nodes in mylist1[:-1]:
	doc = ET.SubElement(root, "row")
	latlong = content[int(nodes)].split(' ')
	ET.SubElement(doc, "lat").text = latlong[1]
	ET.SubElement(doc, "long").text = latlong[2] # may have to switch

tree = ET.ElementTree(root)
tree.write("latlong.xml")
"""
print(mylist1[:-1])
print('\n')
print(mylist2[:-1])
print('\n')
print(mylist3[:-1])
"""
f.close()