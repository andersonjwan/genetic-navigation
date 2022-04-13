from setuptools import Extension, setup
from Cython.Build import cythonize

extensions = [
    Extension(
        name="algorithm",
        sources=["bindings/algorithm.pyx"],
        include_dirs=["src/genalg"]
    ),
    Extension(
        name="crossover",
        sources=["bindings/crossover.pyx"],
        include_dirs=["src/genalg"]
    ),
    Extension(
        name="mutation",
        sources=["bindings/mutation.pyx"],
        include_dirs=["src/genalg"]
    ),
    Extension(
        name="options",
        sources=["bindings/options.pyx",],
        include_dirs=["src/genalg"]
    ),
    Extension(
        name="population",
        sources=["bindings/population.pyx",],
        include_dirs=["src/genalg"]
    ),
    Extension(
        name="selection",
        sources=["bindings/selection.pyx",],
        include_dirs=["src/genalg"]
    ),
    Extension(
        name="individual",
        sources=["bindings/individual.pyx"],
        include_dirs=["src/genalg"]
    ),
]

setup(
    name="py-genalg",
    version="0.0.1",
    ext_package="pygenalg",
    ext_modules=cythonize(extensions),
    install_requires=[
        "numpy",
        "matplotlib",
        "seaborn",
        "pandas"
    ],
    python_requires=">=3.8"
)
