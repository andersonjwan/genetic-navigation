from setuptools import Extension, setup
from Cython.Build import cythonize

extensions = [
    Extension(
        name="pygenalg.algorithm",
        sources=["bindings/pygenalg/algorithm.pyx"],
        include_dirs=["src/genalg"]
    ),
    Extension(
        name="pygenalg.core.options",
        sources=["bindings/pygenalg/core/options.pyx"],
        include_dirs=["src/genalg"]
    )
]

setup(
    name="py-genalg",
    version="0.0.1",
    ext_modules=cythonize(extensions),
    python_requires=">=3.8"
)
