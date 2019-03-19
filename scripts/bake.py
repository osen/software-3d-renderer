import bpy

def unselect_all():
	for obj in bpy.data.objects:
		obj.select = False

	bpy.context.scene.objects.active = None

def set_active(obj):
	unselect_all()
	obj.select = True
	bpy.context.scene.objects.active = obj

def lightmap_unwrap(obj):
	print("Generating light map [" + obj.name + "]")
	set_active(obj)

	bakeMap = obj.data.uv_textures.new("BakeMap")
	bakeMap.active = True;
	image = bpy.data.images.new(obj.name + "_bake", width=2048, height=2048)
	image.filepath = obj.name + "_bake.png"

	for face in obj.data.polygons:
		face.select = True

	bpy.ops.object.mode_set(mode = 'EDIT')
	bpy.data.screens['UV Editing'].areas[1].spaces[0].image = image
	bpy.ops.uv.lightmap_pack()
	bpy.ops.object.mode_set(mode = 'OBJECT')

	for face in obj.data.polygons:
		face.select = False

	return image

def strip_none(obj):
	print("Removing textureless faces [" + obj.name + "]")
	set_active(obj)
	mesh = obj.data
	selected = 0

	for face in mesh.polygons:
		material = mesh.materials[face.material_index]
		if material.active_texture == None:
			face.select = True
			selected = selected + 1
		else:
			face.select = False

	if selected > 0:
		bpy.ops.object.mode_set(mode = 'EDIT')
		bpy.ops.mesh.delete(type='FACE')
		bpy.ops.object.mode_set(mode = 'OBJECT')

def perform_bake(obj, image):
	print("Performing bake [" + obj.name + "]")

	if len(obj.data.polygons) < 1:
		print("Nothing to bake [" + obj.name + "]")
		return

	#bpy.data.scenes["Scene"].render.bake_type = 'SHADOW'
	bpy.ops.object.bake_image()
	#image.save()
	image.save_render(image.filepath)

def bake_scene():
	outPath = bpy.path.display_name_from_filepath(bpy.context.blend_data.filepath)
	bpy.ops.object.mode_set(mode = 'OBJECT')
	unselect_all()

	for obj in bpy.data.objects:
		if obj.type == "MESH":
			obj.data.name = obj.name + "Mesh"

	bpy.ops.export_scene.obj(
		filepath=outPath + ".obj",
		path_mode='COPY')

	for obj in bpy.data.objects:
		if obj.type == "MESH":
			obj.select = True;
			bpy.ops.object.delete()

	bpy.ops.import_scene.obj(filepath = outPath + ".obj")

	for obj in bpy.data.objects:
		if obj.type == "MESH":
			strip_none(obj)

			if obj.name != "NoBake_NoBakeMesh":
				image = lightmap_unwrap(obj)
				perform_bake(obj, image)

	bpy.ops.export_scene.obj(
		filepath=outPath + "_lightmap.obj",
		path_mode='RELATIVE')

bake_scene()

