import bpy

def unselect_all():
	for obj in bpy.data.objects:
		obj.select = False

def set_active(obj):
	unselect_all()
	obj.select = True
	bpy.context.scene.objects.active = obj

def load_obj(path):
	unselect_all()
	bpy.ops.import_scene.obj(filepath = path)

	for obj in bpy.data.objects:
		if obj.select == True:
			unselect_all()
			return obj

	unselect_all()

	return None

def lightmap_unwrap(obj):
	print("Generating light map [" + obj.name + "]")
	set_active(obj)
	bpy.ops.object.mode_set(mode = 'EDIT')

	bakeMap = obj.data.uv_textures.new("BakeMap")
	bakeMap.active = True;
	image = bpy.data.images.new(obj.name + "_bake", width=2048, height=2048)
	image.filepath = obj.name + "_bake.png"

	bpy.data.screens['UV Editing'].areas[1].spaces[0].image = image

	bpy.ops.uv.lightmap_pack(PREF_CONTEXT='ALL_FACES')

	bpy.ops.object.mode_set(mode = 'OBJECT')

	return image

def strip_none(obj):
	print("Removing textureless faces [" + obj.name + "]")

	set_active(obj)
	mesh = obj.data

	for face in mesh.polygons:
		material = mesh.materials[face.material_index]
		if material.active_texture == None:
			face.select = True
		else:
			face.select = False

	bpy.ops.object.mode_set(mode = 'EDIT')
	bpy.ops.mesh.delete(type='FACE')
	bpy.ops.object.mode_set(mode = 'OBJECT')
	#bpy.ops.object.select_all(action='SELECT')

	for face in mesh.polygons:
		face.select = True

def perform_bake(obj, image):
	print("Performing bake [" + obj.name + "]")

	if len(obj.data.polygons) < 1:
		print("Nothing to bake [" + obj.name + "]")
		return

	bpy.ops.object.bake_image()
	image.save()

outPath = bpy.path.display_name(bpy.context.blend_data.filepath)
bpy.ops.object.mode_set(mode = 'OBJECT')
bpy.ops.object.select_all(action='DESELECT')

bpy.ops.export_scene.obj(
	filepath=outPath + "_unlit.obj",
	use_selection=False,
	use_materials=True,
	path_mode='RELATIVE')

for obj in bpy.data.objects:
	if obj.type == "MESH":
		unselect_all()
		obj.select = True;
		bpy.ops.object.delete()

model = load_obj(outPath + "_unlit.obj")

for obj in bpy.data.objects:
	if obj.type == "MESH":
		strip_none(obj)
		image = lightmap_unwrap(obj)
		perform_bake(obj, image)

bpy.ops.export_scene.obj(
	filepath=outPath + ".obj",
	use_materials=True,
	path_mode='RELATIVE')

