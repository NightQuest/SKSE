Scriptname NetImmerse Hidden

; Return whether the object has the particular node
bool Function HasNode(ObjectReference ref, string node, bool firstPerson) native global

; NiNode Manipulation
float Function GetNodePositionX(ObjectReference ref, string node, bool firstPerson) native global
float Function GetNodePositionY(ObjectReference ref, string node, bool firstPerson) native global
float Function GetNodePositionZ(ObjectReference ref, string node, bool firstPerson) native global

; Returns nodeB - nodeA
float Function GetRelativeNodePositionX(ObjectReference ref, string nodeA, string nodeB, bool firstPerson) native global
float Function GetRelativeNodePositionY(ObjectReference ref, string nodeA, string nodeB, bool firstPerson) native global
float Function GetRelativeNodePositionZ(ObjectReference ref, string nodeA, string nodeB, bool firstPerson) native global

Function SetNodePositionX(ObjectReference ref, string node, float x, bool firstPerson) native global
Function SetNodePositionY(ObjectReference ref, string node, float y, bool firstPerson) native global
Function SetNodePositionZ(ObjectReference ref, string node, float z, bool firstPerson) native global


; Sets the scale of a particular Nif node
float Function GetNodeScale(ObjectReference ref, string node, bool firstPerson) native global
Function SetNodeScale(ObjectReference ref, string node, float scale, bool firstPerson) native global

; Sets a NiTriShape's textures by name of the Nif node
Function SetNodeTextureSet(ObjectReference ref, string node, TextureSet tSet, bool firstPerson) native global