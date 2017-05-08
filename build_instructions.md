[&larr; Back to ClassCreator](index.md)

# Building ClassCreator
To automatically copy the **template** directory to the build directory an additional building step has to be added in Qt Creator:

1. Open **Build Settings** (**Projects** tab on the left side)
2. Select the wanted **Build-Configuration**: `Debug` / `Release`
3. Select **Add Build Step** -> **Make**
4. Add for the **Make arguments**: `install`
