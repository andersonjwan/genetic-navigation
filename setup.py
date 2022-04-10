from setuptools import Extension, setup
from Cython.Build import cythonize

extensions = [
    Extension(
        name="algorithm",
        sources=["bindings/algorithmplusplus.pyx"],
        include_dirs=["src"]
    ),
    Extension(
        name="crossover",
        sources=["bindings/crossoverplusplus.pyx"],
        include_dirs=["src"]
    ),
    Extension(
        name="mutation",
        sources=["bindings/mutationplusplus.pyx"],
        include_dirs=["src"]
    ),
    Extension(
        name="options",
        sources=["bindings/optionsplusplus.pyx",],
        include_dirs=["src"]
    ),
    Extension(
        name="population",
        sources=["bindings/populationplusplus.pyx",],
        include_dirs=["src"]
    ),
    Extension(
        name="selection",
        sources=["bindings/selectionplusplus.pyx",],
        include_dirs=["src"]
    ),
    Extension(
        name="individual",
        sources=["bindings/individualplusplus.pyx"],
        include_dirs=["src"]
    ),
]

setup(
    name="py-genalg",
    version="0.0.1",
    ext_package="pygenalg",
    ext_modules=cythonize(extensions),
    python_requires=">=3.8"
)
