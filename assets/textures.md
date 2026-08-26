# How to use the textures

This is a very simplified version of what Minecraft does to store the textures. It consists of a `blocks.png` and `blocks.json` file, which describe all of the blocks. The first one contains all the textures, being 16x16. The second one describes how to insert the textures into the block models.

## Structure of a block

Consists of type of texture and texture IDs, something like this:
```json
"dirt": {
    "type": "cube_all",
    "textures": {
        "all": 0
    }
}
```

Here, we will go through all the different types:

1. **"cube_all"**: a single texture for all the faces, only requires one argument: "all".
2. **"cube_top_bottom"**: three textures for the faces, one for the top, one for the bottom and one for all the sides. The arguments are "top", "bottom" and "side".
3. **"cube_column"**: two textures for the faces, one for the top and bottom and one for all the sides. The arguments are "end" and "side".
4. **"air"**: only for air, doesn't contain any textures.

In addition, they have a **"transparent"** boolean false by default, which defines if faces should be put between blocks (glass, leaves, etc).

TODO: sepparate transparent mesh from opaque mesh.