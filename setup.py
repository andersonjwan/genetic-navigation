from setuptools import Extension, setup
from Cython.Build import cythonize

extensions = [
    Extension(
        name="algorithm",
        sources=["bindings/algorithm.pyx"],
        include_dirs=["src"]
    ),
    Extension(
        name="crossover",
        sources=["bindings/crossover.pyx"],
        include_dirs=["src"]
    ),
    Extension(
        name="mutation",
        sources=["bindings/mutation.pyx"],
        include_dirs=["src"]
    ),
    Extension(
        name="options",
        sources=["bindings/options.pyx",],
        include_dirs=["src"]
    ),
    Extension(
        name="population",
        sources=["bindings/population.pyx",],
        include_dirs=["src"]
    ),
    Extension(
        name="selection",
        sources=["bindings/selection.pyx",],
        include_dirs=["src"]
    ),
    Extension(
        name="individual",
        sources=["bindings/individual.pyx"],
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
